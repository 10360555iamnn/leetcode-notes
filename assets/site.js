// 首頁篩選
document.querySelectorAll('.filters button').forEach(b => b.addEventListener('click', () => {
  document.querySelectorAll('.filters button').forEach(x => x.setAttribute('aria-pressed', String(x === b)));
  const f = b.dataset.f;
  document.querySelectorAll('.card').forEach(c => { c.hidden = f !== 'all' && c.dataset.series !== f; });
}));

// 程式碼分頁
document.querySelectorAll('.tabs button').forEach(b => b.addEventListener('click', () => {
  const box = b.closest('.code');
  box.querySelectorAll('.tabs button').forEach(x => x.setAttribute('aria-selected', String(x === b)));
  box.querySelectorAll('.pane').forEach(p => { p.hidden = p.dataset.pane !== b.dataset.tab; });
}));

// 複製按鈕
document.querySelectorAll('.copy').forEach(b => b.addEventListener('click', async () => {
  const txt = b.parentElement.querySelector('code').innerText;
  try { await navigator.clipboard.writeText(txt); b.textContent = '已複製！'; }
  catch { b.textContent = '複製失敗'; }
  setTimeout(() => { b.textContent = '複製'; }, 1500);
}));

// C++ 語法上色（highlight.js，載入失敗也不影響閱讀）
if (document.querySelector('pre code')) {
  const s = document.createElement('script');
  s.src = 'https://cdnjs.cloudflare.com/ajax/libs/highlight.js/11.9.0/highlight.min.js';
  s.onload = () => document.querySelectorAll('pre code').forEach(el => window.hljs.highlightElement(el));
  document.head.appendChild(s);
}
