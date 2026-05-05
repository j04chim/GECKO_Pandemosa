class Tick {

	constructor(nb_of_ticks, date, size, x, y) {

		this.nb_of_ticks = nb_of_ticks;
		this.obj = document.createElement("div");
		this.obj.classList.add("timeline_tick");
		this.obj.innerText = date.getDate();
		let timeline = document.getElementById("timeline");
		timeline.appendChild(this.obj);
		this.obj.style.left = x + "px";
		this.obj.style.top = y + "px";
		this.o_x = x;
		this.o_y = y;
		this.size = size;
		this.date = new Date(date);

	}

	moveright(nb) {
		this.o_x += (nb * (this.size / this.nb_of_ticks))
		this.obj.style.left = this.o_x + "px";
	}

	select() {
		this.obj.style.border = "solid 2px red";
		return this;
	}

	unselect() {
		this.obj.style.border = "solid 2px transparent";
	}

	getDate() {
		return this.date;
	}

	delete() {
		this.obj.remove();
	}

}

class Timeline {

	constructor(start, ticks) {
		let day = parseInt(start.split("-")[2]);
		let month = parseInt(start.split("-")[1]);
		let year = parseInt(start.split("-")[0]);
		this.ticks = ticks;
		this.current = new Date(year, month, day);

		this.obj = document.createElement("div");
		this.obj.classList.add("timeline_text");
		this.obj.style.top = window.screen.height - 200 + "px";
		this.obj.style.left = 50 + "px";
		this.obj.innerText = this.current.toDateString();
		let timeline = document.getElementById("timeline");
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
		let tmp = new Tick(this.ticks, this.current, document.body.clientWidth - 100, 50, window.screen.height - 150);
		this.time.push(tmp);
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