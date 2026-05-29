class Pandemosa {

    constructor(url) {

        this.events = [];
        this.notes = [];
        this.timeline = null;
        this.network = new Network("http://127.0.0.1:8080");
        this.session = null;
        this.current_date = new Date();
        this.menu = null;

    }

    async newSession() {

        this.session = await this.network.createSession();
        let day = parseInt(this.session.ingame_date.split("-")[2]);
        let month = parseInt(this.session.ingame_date.split("-")[1]);
        let year = parseInt(this.session.ingame_date.split("-")[0]);
        this.current_date = new Date(year, month, day);
        localStorage.setItem("session", this.session.id);

    }

    async loadSession(id) {

        this.session = await this.network.getSession(id);
        let day = parseInt(this.session.ingame_date.split("-")[2]);
        let month = parseInt(this.session.ingame_date.split("-")[1]);
        let year = parseInt(this.session.ingame_date.split("-")[0]);
        this.current_date = new Date(year, month, day);
        localStorage.setItem("session", this.session.id);

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

    async loadNotes() {

        let notes = await this.network.getNotes();
        for ( let i = 0; i < notes.Notes.length; ++i ) {
            this.notes.push(
                new Note(
                    notes.Notes[i].content,
                    Math.random() * 10000 % (document.body.clientWidth/2 - 200) + document.body.clientWidth/2,
                    Math.random() * 10000 % (window.screen.height - 300),
                    this.network,
                    notes.Notes[i].id
                )
            );

        };
        this.notes.forEach((n) => {
            n.loaded = false;
        });
         let notelink = await this.network.getNoteLink();
         for ( let i = 0; i < notelink.NoteLink.length; ++i ) {
            this.notes.forEach((n) => {
                if (n.id == notelink.NoteLink[i].note_a ||
                    n.id == notelink.NoteLink[i].note_b
                ) {
                    n.link();
                }
            });
            if (LINE)
                LINE.destroy();
            LINE = null;
         };
        this.notes.forEach((n) => {
            n.loaded = true;
        });
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

    async createNewGame() {
        await this.newSession();
        await this.loadEvents();
        this.loadTimeline();
    }

    async loadGame(id) {
        await this.loadSession(id);
        await this.loadEvents();
        await this.loadNotes();
        this.loadTimeline();
    }

    displayGame() {

        if (this.obj)
            this.obj.remove();
        if (this.menu) {
            this.menu.destroy();
            this.menu = null;
        }

        this.obj = document.createElement("div");
        let lines = document.createElement("div");
        let notes = document.createElement("div");
        let events = document.createElement("div");
        let timeline = document.createElement("div");
        let buttons = document.createElement("div");
        let addnote = document.createElement("button");

        addnote.addEventListener("click", async (e) => {
            let note = await this.network.createNote({tt: "", ct: ""});
            console.log(note);
            new Note(
                "",
                Math.random() * 10000 % (document.body.clientWidth/2 - 200) + document.body.clientWidth/2,
                Math.random() * 10000 % (window.screen.height - 300),
                this.network,
                note.id
            );
        });
        document.addEventListener("mousemove", (e) => {
            if (LINE) LINE.setEnd(e.pageX - 100, e.pageY);
        })

        lines.id = "lines";
        notes.id = "notes";
        events.id = "events";
        timeline.id = "timeline";
        addnote.id = "addnote";
        buttons.id = "buttonbar";
        this.obj.id = "pandemosa";

        buttons.appendChild(addnote);

        this.obj.appendChild(lines);
        this.obj.appendChild(notes);
        this.obj.appendChild(events);
        this.obj.appendChild(timeline);
        this.obj.appendChild(buttons);

        document.body.appendChild(this.obj);

    }

    displayWelcome() {
        this.obj = document.createElement("div");
        this.obj.id = "pandemosa";
        document.body.appendChild(this.obj);
        this.menu  = new Menu(
            this,
            Math.random() * 10000 % (document.body.clientWidth - 200),
            Math.random() * 10000 % (window.screen.height - 200)
        );
    }

}