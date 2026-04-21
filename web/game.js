'use strict';
// Space Destruction — Web Reboot
// Original C++ game by Luca Veschi, 2014
// Web version 2024

// ─── RENDERING CONSTANTS ────────────────────────────────────────────────────

const FONT_PX  = 13;
const FONT     = `${FONT_PX}px "Courier New", Courier, monospace`;
const COLS     = 135;
const ROWS     = 51;
const FG       = '#00cc00';
const DIM      = '#006600';
const YEL      = '#ffff00';
const RED      = '#ff3333';
const WHT      = '#cccccc';

// Game area bounds (matching original console layout)
const GL = 2, GR = 110, GT = 2, GB = 49;
const SX = 113; // sidebar x start

let canvas, ctx, CW, CH;

// Character grid: each cell is {ch, col}
let grid;

function gIdx(x, y)              { return (y - 1) * COLS + (x - 1); }
function gc(x, y, ch, col = FG)  {
  if (x < 1 || x > COLS || y < 1 || y > ROWS) return;
  const i = gIdx(x, y);
  grid[i] = { ch, col };
}
function gs(x, y, s, col = FG)   { for (let i = 0; i < s.length; i++) gc(x + i, y, s[i], col); }
function clearGrid()              { grid = Array.from({ length: COLS * ROWS }, () => ({ ch: ' ', col: FG })); }

function render() {
  ctx.fillStyle = '#000';
  ctx.fillRect(0, 0, canvas.width, canvas.height);
  ctx.font = FONT;
  for (let y = 1; y <= ROWS; y++) {
    for (let x = 1; x <= COLS; x++) {
      const { ch, col } = grid[gIdx(x, y)];
      if (ch !== ' ') {
        ctx.fillStyle = col;
        ctx.fillText(ch, (x - 1) * CW, y * CH - 2);
      }
    }
  }
}

// ─── INPUT ──────────────────────────────────────────────────────────────────

const held    = {};
const pressed = {};
const CTRL_KEYS = ['ArrowLeft','ArrowRight','ArrowUp','ArrowDown',' ','Escape','Enter','Backspace'];

window.addEventListener('keydown', e => {
  if (CTRL_KEYS.includes(e.key)) e.preventDefault();
  if (!held[e.key]) pressed[e.key] = true;
  held[e.key] = true;
});
window.addEventListener('keyup', e => { held[e.key] = false; });
function flushPressed() { for (const k in pressed) delete pressed[k]; }

// ─── GAME STATE ─────────────────────────────────────────────────────────────

let screen;        // 'loading' | 'menu' | 'name' | 'game' | 'paused' | 'over' | 'win' | 'credits'
let t = 0;         // global tick (increments every loop)
let screenT = 0;   // resets when screen changes

let playerName = '';
let record     = 0;
let nameKbHandler = null;

// Player
let px, py, pdir;  // col, row, direction (0=left 1=right)

// Stats
let lives, missiles, score, level, velo;

// Enemies — each: {x, y, ch, minScore, minLevel}
let enemies;

// Bullet — {x, y, dir} | null
let blt;

// Boss
let bossX, bossY;
let bossH1, bossH2, bossL, bossL2;
let bossWallT;

// Internal game-loop sub-counters
let enemyT, scoreT, missileT, moveT, bulletT;

// ─── HELPERS ────────────────────────────────────────────────────────────────

function switchScreen(name) {
  screen  = name;
  screenT = 0;
}

function drawBox(x1, y1, x2, y2, col = FG) {
  for (let x = x1; x <= x2; x++) { gc(x, y1, '-', col); gc(x, y2, '-', col); }
  for (let y = y1; y <= y2; y++) { gc(x1, y, '|', col); gc(x2, y, '|', col); }
  gc(x1, y1, '+', col); gc(x2, y1, '+', col);
  gc(x1, y2, '+', col); gc(x2, y2, '+', col);
}

// ─── LOADING ────────────────────────────────────────────────────────────────

function goLoading() {
  clearGrid();
  switchScreen('loading');
}

function tickLoading() {
  if (screenT === 1)   gs(1, 1, 'LOAD');
  if (screenT === 200) gc(5, 1, '.');
  if (screenT === 400) gc(6, 1, '.');
  if (screenT === 600) gc(7, 1, '.');
  if (screenT === 800) goMenu();
}

// ─── MENU ────────────────────────────────────────────────────────────────────

function goMenu() {
  clearGrid();
  switchScreen('menu');

  drawBox(8, 1, 48, 18);
  gs(14, 4,  'BENVENUTO IN THE');
  gs(12, 6,  '  SPACE DESTRUCTION', YEL);
  gs(12, 9,  '  [ENTER]  GIOCA');
  gs(12, 11, '  [ESC]    ESCI');
  gs(100, ROWS, 'DEV. LUCA VESCHI 2014', DIM);
}

function tickMenu() {
  const spin = ['/', '-', '|', '\\'];
  const f = Math.floor(screenT / 20) % 4;
  gc(10, 6, spin[f], YEL);
  gc(33, 6, spin[(f + 2) % 4], YEL);

  if (pressed['Enter'] || pressed[' ']) goName();
  if (pressed['Escape'])                goCredits();
}

// ─── NAME ENTRY ──────────────────────────────────────────────────────────────

function goName() {
  clearGrid();
  switchScreen('name');
  playerName = '';
  gs(50, 25, 'COME TI CHIAMI?');
  gs(50, 26, '[             ]');

  if (nameKbHandler) window.removeEventListener('keydown', nameKbHandler);
  nameKbHandler = (e) => {
    if (screen !== 'name') { window.removeEventListener('keydown', nameKbHandler); nameKbHandler = null; return; }
    if (e.key === 'Enter' && playerName.length > 0) {
      window.removeEventListener('keydown', nameKbHandler); nameKbHandler = null;
      goGame();
    } else if (e.key === 'Backspace') {
      e.preventDefault();
      playerName = playerName.slice(0, -1);
    } else if (e.key.length === 1 && playerName.length < 13) {
      playerName += e.key.toUpperCase();
    }
  };
  window.addEventListener('keydown', nameKbHandler);
}

function tickName() {
  const cursor  = Math.floor(screenT / 30) % 2 ? '_' : ' ';
  const display = (playerName + cursor).padEnd(13, ' ');
  gs(51, 26, display);
}

// ─── GAME ────────────────────────────────────────────────────────────────────

function goGame() {
  clearGrid();
  switchScreen('game');

  px = 20; py = 20; pdir = 1;
  lives = 5; missiles = 5; score = 0; level = 1; velo = 5;
  blt = null;
  enemyT = 0; scoreT = 0; missileT = 0; moveT = 0; bulletT = 0;

  // Boss: fixed random position within safe inner area
  bossX  = 15 + Math.floor(Math.random() * 75);
  bossY  = 8  + Math.floor(Math.random() * 33);
  bossH1 = 2; bossH2 = 48;
  bossL  = 0; bossL2 = 109;
  bossWallT = 0;

  // Enemies — positions and activation thresholds from original
  enemies = [
    { x: 10,  y: 10, ch: '*',  minScore: 0,  minLevel: 0 },
    { x: 43,  y: 17, ch: '|',  minScore: 0,  minLevel: 0 },
    { x: 30,  y: 45, ch: '#',  minScore: 0,  minLevel: 0 },
    { x: 24,  y: 28, ch: '-',  minScore: 10, minLevel: 0 },
    { x: 50,  y: 25, ch: '%',  minScore: 10, minLevel: 0 },
    { x: 45,  y: 46, ch: ':',  minScore: 0,  minLevel: 2 },
    { x: 100, y: 45, ch: 'o',  minScore: 10, minLevel: 0 },
    { x: 3,   y: 20, ch: '+',  minScore: 0,  minLevel: 2 },
    { x: 36,  y: 10, ch: 'o',  minScore: 0,  minLevel: 2 },
    { x: 43,  y: 32, ch: 'o',  minScore: 0,  minLevel: 3 },
    { x: 34,  y: 34, ch: 'o',  minScore: 0,  minLevel: 3 },
    { x: 56,  y: 23, ch: '!',  minScore: 0,  minLevel: 3 },
  ];

  drawBorders();
  drawSidebar();
  gs(SX, 18, `CIAO ${playerName}!`, YEL);
}

function drawBorders() {
  const h = '-'.repeat(GR - GL + 1);
  gs(GL, 1,  h);
  gs(GL, 50, h);
  for (let y = 2; y <= 49; y++) { gc(GL - 1, y, '|'); gc(GR + 1, y, '|'); }
}

function drawSidebar() {
  gs(SX, 3,  'VITE:');
  gs(SX, 5,  'PUNTI:');
  gs(SX, 7,  'LIVELLO:');
  gs(SX, 9,  'X:    Y:');
  gs(SX, 11, 'MISSILI:');
  gs(SX, 13, `RECORD: ${record}`, DIM);
  gs(SX, ROWS, 'DEV. LUCA VESCHI', DIM);
}

function updateSidebar() {
  gs(SX + 6,  3,  String(lives).padEnd(3));
  gs(SX + 7,  5,  String(score).padEnd(6));
  gs(SX + 9,  7,  String(level).padEnd(3));
  gs(SX + 3,  9,  String(px).padEnd(4));
  gs(SX + 8,  9,  String(py).padEnd(4));
  gs(SX + 9,  11, String(missiles).padEnd(3));
}

function drawShip(col = FG) {
  if (pdir === 0) {
    gs(px, py - 1, '   /|', col);
    gs(px, py,     '-[##]=', col);
    gs(px, py + 1, '   \\|', col);
  } else {
    gs(px, py - 1, '|\\   ', col);
    gs(px, py,     '=[##]-', col);
    gs(px, py + 1, '|/   ', col);
  }
}

function eraseShip() {
  gs(px, py - 1, '      ');
  gs(px, py,     '      ');
  gs(px, py + 1, '      ');
}

function activeEnemies() {
  return enemies.filter(e => score >= e.minScore && level > e.minLevel);
}

function moveEnemies() {
  for (const e of activeEnemies()) {
    gc(e.x, e.y, ' ');
    const d = Math.floor(Math.random() * 4);
    if      (d === 0) e.x++;
    else if (d === 1) e.y++;
    else if (d === 2) e.x--;
    else              e.y--;
    // wrap (matching original bounds)
    if (e.x >= 102) e.x = 4;  else if (e.x <= 3) e.x = 101;
    if (e.y >= 49)  e.y = 4;  else if (e.y <= 3) e.y = 47;
  }
}

function drawEnemies() {
  for (const e of activeEnemies()) gc(e.x, e.y, e.ch, FG);
}

function checkCollisions() {
  for (const e of activeEnemies()) {
    if (e.x === px && e.y === py) {
      eraseShip();
      lives--;
      px = 50; py = 25;
      if (lives <= 0) { goOver(); return false; }
    }
  }
  return true;
}

function handleInput() {
  moveT--;
  let moved = false;

  if (held['ArrowLeft'])       { eraseShip(); px = Math.max(GL, px - 1);      pdir = 0; moved = true; }
  else if (held['ArrowRight']) { eraseShip(); px = Math.min(GR - 5, px + 1);  pdir = 1; moved = true; }
  if (held['ArrowUp'])         { eraseShip(); py = Math.max(GT + 1, py - 1);            moved = true; }
  else if (held['ArrowDown'])  { eraseShip(); py = Math.min(GB - 1, py + 1);            moved = true; }
  if (moved && moveT <= 0) moveT = 3;

  if (pressed[' '] && !blt && missiles > 0) {
    missiles--;
    const bx = pdir === 1 ? px + 6 : px - 2;
    blt = { x: bx, y: py, dir: pdir };
  }
  if (pressed['Escape']) goPaused();
}

function updateBullet() {
  if (!blt) return;
  gc(blt.x, blt.y, ' ');
  blt.x += blt.dir === 1 ? 3 : -3;

  if (blt.x >= GR || blt.x <= GL) { blt = null; return; }

  // Boss hit check (level 5+)
  if (level >= 5) {
    if (blt.y === bossY && blt.x >= bossX && blt.x <= bossX + 2) {
      blt = null;
      goWin();
      return;
    }
  }

  gc(blt.x, blt.y, '-', YEL);
}

function tickBoss() {
  // Boss ship drawn at fixed position
  gs(bossX, bossY, '/*\\', RED);

  bossWallT++;
  if (bossWallT >= 20) {
    bossWallT = 0;
    bossH1++; bossH2--;
    bossL++;  bossL2--;

    // Horizontal walls
    for (let x = bossL; x <= bossL2; x++) {
      gc(x, bossH1, '*', RED);
      gc(x, bossH2, '*', RED);
    }
    // Vertical walls
    for (let y = bossH1; y <= bossH2; y++) {
      gc(bossL,  y, '*', RED);
      gc(bossL2, y, '*', RED);
    }
  }

  // Player caught by walls?
  if (py <= bossH1 || py >= bossH2 || px <= bossL || px + 5 >= bossL2 || bossH1 >= bossH2) {
    goOver();
  }
}

function tickGame() {
  screenT++;
  enemyT++;  scoreT++;  missileT++;  bulletT++;

  // Level / speed progression (faithful to original score thresholds)
  if (score >= 10 && level < 2) { level = 2; velo = 4; }
  if (score >= 20 && level < 3) { level = 3; velo = 3; }
  if (score >= 30 && level < 4) { level = 4; velo = 2; }
  if (score >= 50)               { velo = 1; }
  if (score >= 70 && level < 5) { level = 5; velo = 1; }

  handleInput();
  if (screen !== 'game') return;

  // Bullet moves every 2 ticks
  if (bulletT >= 2) { bulletT = 0; updateBullet(); }
  if (screen !== 'game') return;

  // Enemy movement every `velo` ticks
  if (enemyT >= velo) {
    enemyT = 0;
    moveEnemies();
    if (!checkCollisions()) return;
    drawEnemies();
    if (level >= 5) tickBoss();
    if (screen !== 'game') return;
  }

  // Score: +1 every 100 ticks (≈ 0.5s)
  if (scoreT >= 100) { scoreT = 0; score++; }

  // Missile reload: 1 missile every ~10 seconds (2000 ticks)
  if (missileT >= 2000 && missiles < 5) { missileT = 0; missiles++; }

  drawShip();
  updateSidebar();
}

// ─── PAUSED ──────────────────────────────────────────────────────────────────

function goPaused() {
  switchScreen('paused');
  clearGrid();
  drawBox(18, 2, 72, 22);
  gs(22, 4,  '=== PAUSA ===', YEL);
  gs(22, 7,  'FRECCE      muovi nave');
  gs(22, 8,  'SPAZIO      spara');
  gs(22, 9,  'ESC         pausa / riprendi');
  gs(22, 12, `Vite:     ${lives}`);
  gs(22, 13, `Missili:  ${missiles}   (ricarica automatica)`);
  gs(22, 14, `Punti:    ${score}`);
  gs(22, 16, `Livello:  ${level}`);
  gs(22, 19, '[ENTER]  Continua');
  gs(22, 20, '[ESC]    Torna al menu');
}

function tickPaused() {
  if (pressed['Enter']) {
    switchScreen('game');
    clearGrid();
    drawBorders();
    drawSidebar();
    drawShip();
    updateSidebar();
  }
  if (pressed['Escape']) goMenu();
}

// ─── GAME OVER ───────────────────────────────────────────────────────────────

function goOver() {
  if (score > record) { record = score; localStorage.setItem('spd_record', String(record)); }
  switchScreen('over');
  clearGrid();
  drawBox(8, 1, 60, 20, RED);
  gs(14, 3,  '*** GAME  OVER ***', RED);
  gs(14, 5,  `GIOCATORE: ${playerName}`);
  gs(14, 7,  `PUNTEGGIO: ${score}`);
  if (score >= record && score > 0) {
    gs(14, 9,  'NUOVO RECORD!! COMPLIMENTI!!', YEL);
  } else {
    gs(14, 9,  `RECORD: ${record}`, DIM);
  }
  gs(14, 13, '[ENTER]  Ricomincia');
  gs(14, 15, '[ESC]    Menu principale');
}

function tickOver() {
  if (pressed['Enter'])   goGame();
  if (pressed['Escape'])  goMenu();
}

// ─── VICTORY ─────────────────────────────────────────────────────────────────

function goWin() {
  if (score > record) { record = score; localStorage.setItem('spd_record', String(record)); }
  switchScreen('win');
  clearGrid();
  drawBorders();
  gs(bossX - 3, bossY, '*** BOOOOM! ***', RED);
  gs(38, 20, '*** HAI VINTO!! ***', YEL);
  gs(38, 22, `PUNTEGGIO: ${score}`);
  if (score >= record && score > 0) {
    gs(38, 24, 'NUOVO RECORD!! COMPLIMENTI!!', YEL);
  } else {
    gs(38, 24, `RECORD: ${record}`, DIM);
  }
  gs(38, 27, '[ENTER]  Ricomincia   [ESC]  Menu');
}

function tickWin() {
  if (pressed['Enter'])  goGame();
  if (pressed['Escape']) goMenu();
}

// ─── CREDITS ─────────────────────────────────────────────────────────────────

function goCredits() {
  clearGrid();
  switchScreen('credits');
  gs(5, 5,  'SPACE DESTRUCTION', YEL);
  gs(5, 7,  'Originale C++ per Windows — Luca Veschi, 2014 (c)');
  gs(5, 9,  'Web reboot 2024 — HTML5 Canvas');
  gs(5, 13, '[ENTER]  Torna al menu');
}

function tickCredits() {
  if (pressed['Enter'] || pressed[' ']) goMenu();
}

// ─── MAIN LOOP ───────────────────────────────────────────────────────────────

function loop() {
  t++;
  // screenT is incremented per-screen (tickGame manages its own; others use the outer increment)
  if (screen !== 'game') screenT++;

  switch (screen) {
    case 'loading':  tickLoading(); break;
    case 'menu':     tickMenu();    break;
    case 'name':     tickName();    break;
    case 'game':     tickGame();    break;
    case 'paused':   tickPaused();  break;
    case 'over':     tickOver();    break;
    case 'win':      tickWin();     break;
    case 'credits':  tickCredits(); break;
  }

  render();
  flushPressed();
}

// ─── INIT ────────────────────────────────────────────────────────────────────

function init() {
  canvas = document.getElementById('c');
  ctx    = canvas.getContext('2d');

  ctx.font = FONT;
  CW = ctx.measureText('M').width;
  CH = Math.ceil(FONT_PX * 1.5);

  canvas.width  = Math.ceil(COLS * CW);
  canvas.height = ROWS * CH;

  // Responsive scaling via CSS
  const maxW  = window.innerWidth - 16;
  const scale = Math.min(1, maxW / canvas.width);
  if (scale < 1) {
    canvas.style.width  = Math.floor(canvas.width  * scale) + 'px';
    canvas.style.height = Math.floor(canvas.height * scale) + 'px';
  }

  record = parseInt(localStorage.getItem('spd_record') || '0', 10);
  clearGrid();
  goLoading();
  setInterval(loop, 5);
}

window.addEventListener('load', init);
