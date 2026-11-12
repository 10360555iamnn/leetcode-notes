const $ = (s, r = document) => r.querySelector(s);
const $$ = (s, r = document) => [...r.querySelectorAll(s)];

// 深色模式切換（記在這台瀏覽器）
$('#theme-btn')?.addEventListener('click', () => {
  const root = document.documentElement;
  const dark = root.dataset.theme ? root.dataset.theme === 'dark' : matchMedia('(prefers-color-scheme: dark)').matches;
  root.dataset.theme = dark ? 'light' : 'dark';
  try { localStorage.setItem('theme', root.dataset.theme); } catch {}
});

// 手機選單
$('#menu-btn')?.addEventListener('click', e => {
  const open = $('#nav-links').classList.toggle('open');
  e.currentTarget.setAttribute('aria-expanded', String(open));
});

// 往下捲時藏起導覽列，往上捲再出現
let lastY = scrollY;
addEventListener('scroll', () => {
  const y = scrollY;
  $('#nav')?.classList.toggle('hide', y > lastY && y > 200 && !$('#nav-links').classList.contains('open'));
  lastY = y;
}, { passive: true });

// 首頁：依網址 #系列 或 #tag:標籤 篩選，再用 ?page=N 分頁（一頁 10 篇）
const PER_PAGE = 10;
const curPage = () => Math.max(1, parseInt(new URLSearchParams(location.search).get('page'), 10) || 1);
function gotoPage(n) {
  const u = new URL(location.href);
  if (n > 1) u.searchParams.set('page', n); else u.searchParams.delete('page');
  history.pushState(null, '', u);
  applyFilter(true);
}
function applyFilter(fromPager) {
  const posts = $$('.post');
  if (!posts.length) return;
  const key = decodeURIComponent(location.hash.slice(1));
  const isTag = key.startsWith('tag:'), val = isTag ? key.slice(4) : key;
  const valid = val && val !== 'categories' && posts.some(p => (isTag ? p.dataset.tags.split('|') : [p.dataset.series]).includes(val));
  const match = posts.filter(p => !valid || (isTag ? p.dataset.tags.split('|').includes(val) : p.dataset.series === val));
  const pages = Math.max(1, Math.ceil(match.length / PER_PAGE));
  const page = Math.min(curPage(), pages);
  const shown = match.slice((page - 1) * PER_PAGE, page * PER_PAGE);
  posts.forEach(p => { p.hidden = !shown.includes(p); });
  // 重新左右交錯
  shown.forEach((p, i) => { p.classList.toggle('left', i % 2 === 0); p.classList.toggle('right', i % 2 === 1); });
  const pager = $('#pager');
  if (pager) {
    const btn = (n, txt, aria) => `<button type="button" data-page="${n}"${aria ? ` class="arrow" aria-label="${aria}"` : n === page ? ' aria-current="page"' : ''}>${txt}</button>`;
    pager.innerHTML = (page > 1 ? btn(page - 1, '‹', '上一頁') : '')
      + Array.from({ length: pages }, (_, i) => btn(i + 1, i + 1)).join('')
      + (page < pages ? btn(page + 1, '›', '下一頁') : '');
    $$('button', pager).forEach(b => b.addEventListener('click', () => gotoPage(+b.dataset.page)));
  }
  const head = $('#cat-head');
  head.hidden = !valid;
  if (valid) { $('#cat-title').textContent = (isTag ? '# ' : '') + val; $('#cat-count').textContent = `${match.length} 支影片`; }
  $$('.side-nav a').forEach(a => a.classList.toggle('on', valid ? a.dataset.seriesLink === val : !a.dataset.seriesLink));
  if (fromPager === true) (valid ? head : $('.posts')).scrollIntoView({ behavior: 'smooth', block: 'start' });
  else if (valid) head.scrollIntoView({ behavior: 'smooth', block: 'start' });
  $('#nav-links')?.classList.remove('open');
}
// 換篩選條件就回到第 1 頁
addEventListener('hashchange', () => {
  const u = new URL(location.href);
  if (u.searchParams.has('page')) { u.searchParams.delete('page'); history.replaceState(null, '', u); }
  applyFilter();
});
addEventListener('popstate', () => applyFilter(true));
applyFilter();

// 程式碼分頁
function showTab(box, i) {
  $$('.tabs button', box).forEach(b => b.setAttribute('aria-selected', String(b.dataset.tab === String(i))));
  $$('.pane', box).forEach(p => { p.hidden = p.dataset.pane !== String(i); });
}
$$('.tabs button').forEach(b => b.addEventListener('click', () => showTab(b.closest('.code'), b.dataset.tab)));
$$('[data-goto-tab]').forEach(a => a.addEventListener('click', () => { const box = $('.code'); if (box) showTab(box, a.dataset.gotoTab); }));

// 目錄：捲動時標出目前段落
const secs = $$('.sec');
if (secs.length && $('.toc')) {
  const links = $$('.toc li:not(.sub) a');
  const io = new IntersectionObserver(es => es.forEach(e => {
    if (e.isIntersecting) links.forEach(a => a.classList.toggle('on', a.getAttribute('href') === '#' + e.target.id));
  }), { rootMargin: '-80px 0px -60% 0px' });
  secs.forEach(s => io.observe(s));
}

// 複製按鈕
$$('.copy').forEach(b => b.addEventListener('click', async () => {
  const txt = b.closest('.pane').querySelector('code').innerText;
  try { await navigator.clipboard.writeText(txt); b.textContent = '已複製！'; }
  catch { b.textContent = '複製失敗'; }
  setTimeout(() => { b.textContent = '複製'; }, 1500);
}));

// 熱力圖在窄螢幕要捲動時，預設顯示最近的日期
$$('.heat-scroll').forEach(el => { el.scrollLeft = el.scrollWidth; });
// 點熱力圖格子：顯示當天發佈的影片（再點一次收起）
$$('.heat-grid i').forEach(cell => cell.addEventListener('click', () => {
  const day = cell.dataset.day, was = cell.classList.contains('sel');
  $$('.heat-grid i.sel').forEach(c => c.classList.remove('sel'));
  $$('.heat-day').forEach(p => { p.hidden = true; });
  if (was) return;
  cell.classList.add('sel');
  const panel = $(`.heat-day[data-day="${day}"]`);
  if (panel) panel.hidden = false;
  else { const none = $('.heat-none'); $('span', none).textContent = day.replace(/-/g, '/'); none.hidden = false; }
}));

// ---- 題目清單：排序與難度篩選 ----
const prList = $('#pr-list');
if (prList) {
  let lvF = null;
  const render = () => {
    $$('li', prList).forEach(li => { li.hidden = !!lvF && li.dataset.lv !== lvF; });
    $$('.lv-box').forEach(b => b.setAttribute('aria-pressed', String(b.dataset.filter === lvF)));
    const f = $('#pr-filter'), n = $$('li', prList).filter(li => !li.hidden).length;
    f.hidden = !lvF; if (lvF) f.innerHTML = `只顯示 ${lvF}（${n} 題）<a href="#" id="pr-clear">顯示全部</a>`;
    $('#pr-clear')?.addEventListener('click', e => { e.preventDefault(); lvF = null; render(); });
  };
  $$('.lv-box').forEach(b => b.addEventListener('click', () => { lvF = lvF === b.dataset.filter ? null : b.dataset.filter; render(); }));
  $$('.pr-tabs [data-sort]').forEach(b => b.addEventListener('click', () => {
    $$('.pr-tabs [data-sort]').forEach(x => x.setAttribute('aria-selected', String(x === b)));
    const items = $$('li', prList);
    items.sort(b.dataset.sort === 'num' ? (x, y) => x.dataset.n - y.dataset.n : (x, y) => y.dataset.date.localeCompare(x.dataset.date) || y.dataset.n - x.dataset.n);
    items.forEach(li => prList.appendChild(li));
  }));
}

// ---- 站內搜尋（Ctrl+K 或 / 開啟） ----
const ALIAS = { 動態規劃: 'dp dynamic programming', 優先佇列: 'heap 堆積 priority_queue pq', 雙指針: 'two pointers 雙指標', 單調棧: 'monotonic stack 單調堆疊 stack', 有序集合: 'set ordered set', 模擬: 'simulation', 記憶化: 'memo memoization', 計數: 'count', 矩陣: 'matrix grid', 前綴最大值: 'prefix max 前綴', 數學: 'math', 貪心: 'greedy 貪婪', 陣列: 'array', 一次掃描: 'one pass 線性掃描 linear scan' };
const ROOT = document.body.dataset.root || '';
const IDX = (window.SEARCH_INDEX || []).map(it => ({ ...it,
  hay: [it.title, it.zh, it.series, it.level, it.desc, ...it.tags, ...it.tags.map(t => ALIAS[t] || ''), ...it.nums.map(String)].join(' ').toLowerCase() }));
const sEl = $('#search'), sIn = $('#search-input'), sRes = $('#search-results');
let sSel = 0;
const escH = s => s.replace(/[&<>"]/g, c => ({ '&': '&amp;', '<': '&lt;', '>': '&gt;', '"': '&quot;' })[c]);
function mark(text, toks) {
  let h = escH(text);
  for (const t of toks) if (t) h = h.replace(new RegExp(t.replace(/[.*+?^${}()|[\]\\]/g, '\\$&'), 'gi'), m => `<mark>${m}</mark>`);
  return h;
}
function runSearch() {
  const toks = sIn.value.trim().toLowerCase().split(/\s+/).filter(Boolean);
  const hits = IDX.map(it => {
    if (!toks.every(t => it.hay.includes(t))) return null;
    let score = 0;
    for (const t of toks) { if (it.nums.some(n => String(n) === t)) score += 10; if (it.title.toLowerCase().includes(t) || it.zh.toLowerCase().includes(t)) score += 5; if (it.tags.some(g => g.toLowerCase().includes(t))) score += 3; }
    return { it, score };
  }).filter(Boolean).sort((a, b) => b.score - a.score);
  sSel = 0;
  sRes.innerHTML = hits.length ? hits.map(({ it }, i) => `<li><a href="${ROOT}${it.url}" class="${i === 0 ? 'on' : ''}">
    <img src="${ROOT}${it.cover}" alt="" loading="lazy"><span class="r-main"><span class="r-title">${mark(it.title, toks)}</span>
    <span class="r-sub">${mark(it.zh, toks)} · ${escH(it.series)} · ${it.level}</span><span class="r-sub">${it.tags.map(t => mark(t, toks)).join('、')}</span></span></a></li>`).join('')
    : `<li class="search-empty">找不到「${escH(sIn.value)}」相關的題目</li>`;
}
function openSearch() { sEl.hidden = false; sIn.value = ''; runSearch(); setTimeout(() => sIn.focus(), 0); document.body.style.overflow = 'hidden'; }
function closeSearch() { sEl.hidden = true; document.body.style.overflow = ''; }
if (sEl) {
  $('#search-btn').addEventListener('click', openSearch);
  $('#search-close').addEventListener('click', closeSearch);
  sEl.addEventListener('click', e => { if (e.target === sEl) closeSearch(); });
  sIn.addEventListener('input', runSearch);
  sIn.addEventListener('keydown', e => {
    const as = $$('a', sRes);
    if (e.key === 'ArrowDown' || e.key === 'ArrowUp') {
      e.preventDefault(); if (!as.length) return;
      sSel = (sSel + (e.key === 'ArrowDown' ? 1 : -1) + as.length) % as.length;
      as.forEach((a, i) => a.classList.toggle('on', i === sSel)); as[sSel].scrollIntoView({ block: 'nearest' });
    } else if (e.key === 'Enter' && as[sSel]) { location.href = as[sSel].href; }
  });
  addEventListener('keydown', e => {
    if (e.key === 'Escape' && !sEl.hidden) closeSearch();
    else if ((e.key === 'k' && (e.ctrlKey || e.metaKey)) || (e.key === '/' && !/INPUT|TEXTAREA/.test(document.activeElement.tagName))) { e.preventDefault(); openSearch(); }
  });
}

// C++ 語法上色（highlight.js，載入失敗也不影響閱讀）
if ($('pre code')) {
  const s = document.createElement('script');
  s.src = 'https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/highlight.min.js';
  s.onload = () => $$('pre code').forEach(el => window.hljs.highlightElement(el));
  document.head.appendChild(s);
}
