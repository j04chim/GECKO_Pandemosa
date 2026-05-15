class Pandemosa {

    constructor(url) {

        this.events = [];
        this.timeline = null;
        this.network = new Network("http://127.0.0.1:8080");
        this.session = null;
        this.current_date = new Date();

    }

    async newSession() {

        this.session = await this.network.createSession();
        let day = parseInt(this.session.ingame_date.split("-")[2]);
        let month = parseInt(this.session.ingame_date.split("-")[1]);
        let year = parseInt(this.session.ingame_date.split("-")[0]);
        this.current_date = new Date(year, month, day);

    }

    async loadSession(id) {

        this.session = await this.network.getSession(id);
        let day = parseInt(this.session.ingame_date.split("-")[2]);
        let month = parseInt(this.session.ingame_date.split("-")[1]);
        let year = parseInt(this.session.ingame_date.split("-")[0]);
        this.current_date = new Date(year, month, day);
    }

    async loadEvents() {

        let events = await this.network.getEvents({dt: this.session.ingame_date});
        for ( let i = 0; i < events.Events.length; ++i ) {
            this.events.push(
                new Event(
                    events.Events[i].title,
                    events.Events[i].summary,
                    Math.random() * 10000 % (document.body.clientWidth/2 - 300),
                    Math.random() * 10000 % (window.screen.height - 600)
                )
            );
        }

    }

    loadTimeline() {

        this.timeline = new Timeline(this.session.ingame_date, 10);

    }

    async nextDay() {
        this.timeline.next();
        this.current_date.setDate(this.current_date.getDate() + 1);
        let events = await this.network.getEvents({dt: this.current_date.getFullYear() + "-" + String(this.current_date.getMonth()).padStart(2, "0") + "-" + String(this.current_date.getDate()).padStart(2, "0")});
        this.events.forEach((e) => {
            e.destroy();
        })
        this.events = [];
        for ( let i = 0; i < events.Events.length; ++i ) {
            this.events.push(
                new Event(
                    events.Events[i].title,
                    events.Events[i].summary,
                    Math.random() * 10000 % (document.body.clientWidth/2 - 300),
                    Math.random() * 10000 % (window.screen.height - 600)
                )
            );
        }
    }

    listenerEventAction() {

    }

    display() {

        this.obj = document.createElement("div");
        let lines = document.createElement("div");
        let notes = document.createElement("div");
        let events = document.createElement("div");
        let timeline = document.createElement("div");
        let buttons = document.createElement("div");
        let addnote = document.createElement("button");

        lines.id = "lines";
        notes.id = "notes";
        events.id = "events";
        timeline.id = "timeline";
        addnote.id = "addnote";
        buttons.id = "buttonbar";

        buttons.appendChild(addnote);

        this.obj.appendChild(lines);
        this.obj.appendChild(notes);
        this.obj.appendChild(events);
        this.obj.appendChild(timeline);
        this.obj.appendChild(buttons);

    }

}