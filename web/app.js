// Lit data.js (ecrit par le simulateur C++) toutes les 500 ms et met la page a jour.
const icons = { Temperature: '🌡️', Humidity: '💧', Sound: '🔊', Light: '💡' };
const ranges = { Temperature: [18, 30], Humidity: [30, 70], Sound: [30, 90] };  // pour les barres
const cards = {};   // id du capteur -> { el, count }
const recent = [];  // dernieres mesures (texte)
let lastTick = -1;
let lastChange = Date.now();

function percent(s) {
  if (s.count === 0) return 0;
  if (s.type === 'Light') return s.value === 'ON' ? 100 : 0;
  const [min, max] = ranges[s.type];
  return Math.max(0, Math.min(100, (parseFloat(s.value) - min) / (max - min) * 100));
}

function makeCard(s) {
  const el = document.createElement('article');
  el.className = 'card ' + s.type;
  el.innerHTML =
    '<div class="card-head">' +
      '<span class="icon">' + icons[s.type] + '</span>' +
      '<div><h3>' + s.type + '</h3><small>Capteur #' + s.id + '</small></div>' +
      '<span class="badge">toutes les ' + s.period + ' s</span>' +
    '</div>' +
    '<div class="value"><span class="num">--</span><span class="unit"></span></div>' +
    '<div class="bar"><div class="bar-fill"></div></div>';
  document.getElementById('grid').appendChild(el);
  return { el: el, count: 0 };
}

function render(d) {
  let measures = 0;
  d.sensors.forEach(function (s) {
    const c = cards[s.id] || (cards[s.id] = makeCard(s));
    measures += s.count;
    c.el.querySelector('.num').textContent = s.value;
    c.el.querySelector('.unit').textContent = s.unit;
    c.el.querySelector('.bar-fill').style.width = percent(s) + '%';
    if (s.type === 'Light') {
      c.el.classList.toggle('on', s.value === 'ON');
      c.el.classList.toggle('off', s.value === 'OFF');
    }
    if (s.count !== c.count) {                  // nouvelle mesure : flash + journal
      c.count = s.count;
      c.el.classList.remove('flash');
      void c.el.offsetWidth;                    // relance l'animation CSS
      c.el.classList.add('flash');
      recent.unshift('[tick ' + d.tick + '] ' + s.type + ' #' + s.id + ' : ' + s.value + ' ' + s.unit);
      if (recent.length > 6) recent.pop();
    }
  });

  document.getElementById('tick').textContent = 'Tick ' + d.tick + ' / ' + d.total;
  document.getElementById('measures').textContent = measures + ' mesures';
  document.getElementById('progress').style.width = (d.tick / d.total * 100) + '%';
  document.getElementById('recent').innerHTML = recent.map(function (t) { return '<li>' + t + '</li>'; }).join('');

  if (d.tick !== lastTick) { lastTick = d.tick; lastChange = Date.now(); }
  const live = Date.now() - lastChange < 3000;
  document.getElementById('dot').classList.toggle('live', live);
  document.getElementById('status').textContent =
    live ? 'Simulation en cours' : (d.tick >= d.total ? 'Simulation terminée' : 'Simulation arrêtée');
}

function poll() {
  const old = document.getElementById('data');
  if (old) old.remove();
  const script = document.createElement('script');
  script.id = 'data';
  script.src = 'data.js?t=' + Date.now();      // evite le cache
  script.onload = function () { if (window.DATA) render(window.DATA); };
  script.onerror = function () {
    document.getElementById('status').textContent = 'Lancez ./simulator depuis le dossier du projet';
  };
  document.body.appendChild(script);
}

setInterval(poll, 500);
poll();
