let EVENTS = []
let TIMELINE = null;
let NETWORK = new Network("http://127.0.0.1:8080");
let SESSION = {};
let CDATE = new Date();

function createSession() {
	SESSION = NETWORK.createSession();
}

async function loadSession(id) {
	SESSION = await NETWORK.getSession(id);
	let events = await NETWORK.getEvents({dt: SESSION.ingame_date});
	for ( let i = 0; i < events.Events.length; ++i ) {
		EVENTS.push(
			new Event(
				events.Events[i].title,
				events.Events[i].summary,
				Math.random() * 10000 % (document.body.clientWidth - 300),
				Math.random() * 10000 % (window.screen.height - 600)
			)
		);
	}
	TIMELINE = new Timeline(SESSION.ingame_date, 10);
	let day = parseInt(SESSION.ingame_date.split("-")[2]);
	let month = parseInt(SESSION.ingame_date.split("-")[1]);
	let year = parseInt(SESSION.ingame_date.split("-")[0]);
	CDATE = new Date(year, month, day);
}

async function nextDay() {
	TIMELINE.next();
	CDATE.setDate(CDATE.getDate() + 1);
	let events = await NETWORK.getEvents({dt: CDATE.getFullYear() + "-" + String(CDATE.getMonth()).padStart(2, "0") + "-" + String(CDATE.getDate()).padStart(2, "0")});
	EVENTS.forEach((e) => {
		e.destroy();
	})
	EVENTS = [];
	for ( let i = 0; i < events.Events.length; ++i ) {
		EVENTS.push(
			new Event(
				events.Events[i].title,
				events.Events[i].summary,
				Math.random() * 10000 % (document.body.clientWidth - 300),
				Math.random() * 10000 % (window.screen.height - 600)
			)
		);
	}
}

loadSession(4);

document.getElementById("create").addEventListener("click", (e) => {
	new Event("asdasd asd asd asd  asd fdg fd g", " sdf sf sdf sdf thdfgfASFDS SDF SDDF SDFAs dh g", Math.random() * 100, Math.random() * 100);
});

document.getElementById("next").addEventListener("click", (e) => {
	nextDay();
});
