class Tick {

	constructor(nb_of_ticks, label, date, size, x, y) {

		this.nb_of_ticks = nb_of_ticks;
		this.obj = document.createElement("div");
		this.obj.classList.add("timeline_tick");
		this.obj.innerText = label;
		let timeline = document.getElementById("timeline");
		timeline.appendChild(this.obj);
		this.obj.style.left = x + "vw";
		this.obj.style.top = y + "vh";
		this.o_x = x;
		this.o_y = y;
		this.size = size;
		this.date = new Date(date);

	}

	moveright(nb) {
		this.o_x += (nb * (this.size / this.nb_of_ticks))
		this.obj.style.left = this.o_x + "vw";
	}

	select() {
		this.obj.style.boxShadow = "0 0 10px 0px red";
		return this;
	}

	unselect() {
        this.obj.style.boxShadow = "";
	}

	getDate() {
		return this.date;
	}

	delete() {
		this.obj.remove();
	}

}

class Timeline {

	constructor(start, ticks, days) {
		let day = parseInt(start.split("-")[2]);
		let month = parseInt(start.split("-")[1]);
		let year = parseInt(start.split("-")[0]);
		this.ticks = ticks;
		this.current = new Date(year, month, day);
		this.day = days - ticks / 2;

		this.obj = document.createElement("div");
        let shadow = document.createElement("div");
		this.obj.classList.add("timeline_text");
        shadow.classList.add("timeline_shadow");
		this.obj.style.top = 88 + "vh";
		this.obj.style.left = 3 + "vw";
		this.obj.innerText = this.current.toDateString();
		let timeline = document.getElementById("timeline");
        timeline.appendChild(shadow);
		timeline.appendChild(this.obj);

		this.current.setDate(this.current.getDate() - ticks / 2 - 1);
		this.time = [];
		this.selected = null;

		for ( let i = 0; i <= ticks; ++i ) {
			this.time.push(0);
		}

		for ( let i = 0; i <= ticks; ++i ) {
			this.next();
		}
		this.selected = this.time[Math.round(this.time.length/2 - 1, 0)].select();

	}

	next() {
		this.current.setDate(this.current.getDate() + 1);
		let tmp = new Tick(this.ticks, this.day, this.current, 90, 3, 93);
		this.time.push(tmp);
		this.day++;
		if ( this.time[0] == 0 ) {
			this.time.shift();
			for ( let i = 0; i < this.time.length - 1; ++i )
				if ( this.time[i] != 0 ) this.time[i].moveright(1);
		} else {
			this.time[0].delete();
			this.time.shift();
			if ( this.selected ) {
				this.selected.unselect();
			}
			this.selected = this.time[Math.round(this.time.length/2 - 1, 0)].select();
			console.log(this.selected.date);
			this.obj.innerText = this.selected.date.toDateString();
			for ( let i = 0; i < this.time.length - 1; ++i )
				this.time[i].moveright(1);
		}
	}

}