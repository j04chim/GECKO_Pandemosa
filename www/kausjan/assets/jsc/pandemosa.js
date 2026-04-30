class Event {

	constructor(title, desc, x, y) {

		this.x = x;
		this.y = y;
		this.rotation = 0;
		this.old_mouse_x = -1;
		this.old_mouse_y = -1;
		this.mouseclick = false;
		this.locked = false;
		this.weight = (Math.random() * 10) % 15;
		if ( this.weight < 6 ) this.weight = 6;

		this.obj = document.createElement("div");
		let header = document.createElement("div");
		let content = document.createElement("div");
		let rtitle = document.createElement("h2");
		let description = document.createElement("p");
		let footer = document.createElement("div");
		let button_pass = document.createElement("button");
		let button_act = document.createElement("button");
		this.button_zoom = document.createElement("button");

		rtitle.innerText = title;
		description.innerText = desc;
		button_act.innerText = "Act";
		button_pass.innerText = "Pass";
		this.button_zoom.innerText = "Zoom";

		button_act.classList.add("event_button");
		button_act.classList.add("event_act");
		button_pass.classList.add("event_button");
		button_pass.classList.add("event_pass");
		footer.classList.add("event_footer");
		rtitle.classList.add("event_title");
		description.classList.add("event_desc");
		content.classList.add("event_content");
		header.classList.add("event_header");
		this.button_zoom.classList.add("event_zoom");
		this.obj.classList.add("event");

		this.zoom = this.zoom.bind(this);
		this.button_zoom.addEventListener("click", this.zoom);

		header.appendChild(this.button_zoom);
		footer.appendChild(button_act);
		footer.appendChild(button_pass);
		content.appendChild(rtitle);
		content.appendChild(description);

		this.obj.appendChild(header);
		this.obj.appendChild(content);
		this.obj.appendChild(footer);

		this.moveto = this.moveto.bind(this);
		this.click = this.click.bind(this);
		this.release = this.release.bind(this);

		this.obj.style.left = this.x + "px";
		this.obj.style.top = this.y + "px";

		this.obj.addEventListener("mousemove", this.moveto);
		this.obj.addEventListener("mousedown", this.click);
		this.obj.addEventListener("mouseup", this.release);
		this.obj.addEventListener("mouseleave", this.release);

		document.getElementById("events").appendChild(this.obj);

		this.zIndex = this.obj.style.zIndex;

	}

	moveto(e) {

		if ( !this.locked && this.mouseclick ) {

			let mvx = e.pageX - this.old_mouse_x;
			let mvy = e.pageY - this.old_mouse_y;
			this.x += mvx;
			this.y += mvy;
			this.obj.style.left = this.x + "px";
			this.obj.style.top = this.y + "px";
			let vy = (e.pageY - 250) - this.y;

			if ( vy > 0 )
				this.rotation += ( Math.acos( mvy / Math.sqrt( Math.pow(mvy, 2) + Math.pow(mvx, 2) ) ) * (180 / Math.PI) * Math.sign(mvx) * -1 ) / 100;
			else
				this.rotation += ( Math.acos( (mvy * -1) / Math.sqrt( Math.pow(mvy, 2) + Math.pow(mvx, 2) ) ) * (180 / Math.PI) * Math.sign(mvx) ) / 100;
			if ( this.rotation > this.weight ) this.rotation = this.weight;
			if ( this.rotation < -this.weight ) this.rotation = -this.weight;
			this.obj.style.rotate = this.rotation + "deg";

			this.old_mouse_x = e.pageX;
			this.old_mouse_y = e.pageY;

		}

	}

	click(e) {
		if ( !this.locked ) {
				this.mouseclick = true;
			this.old_mouse_x = e.pageX;
			this.old_mouse_y = e.pageY;
			this.obj.style.zIndex = "999";
		}
	}

	release(e) {
		if ( !this.locked ) {
			this.mouseclick = false;
			this.obj.style.zIndex = this.zIndex;
		}
	}

	zoom(e) {
		if ( !this.locked ) {
			this.locked = true;
			this.background = document.createElement("div");
			this.background.style.backgroundColor = "rgba(0, 0, 0, 0.5)";
			this.background.style.backdropFilter = "blur(10px)";
			this.background.style.width = "200vw";
			this.background.style.height = "200vh";
			this.background.style.position = "absolute";
			this.background.style.overflow = "hidden";
			this.background.style.zIndex = "998";
			this.background.style.top = "-100px";
			this.background.style.left = "-100px";
			this.obj.style.zIndex = "999";
			this.obj.style.left = ((document.body.clientWidth / 2) - 150) + "px";
			this.obj.style.top = ((window.screen.height / 2) - 250) + "px";
			this.obj.style.rotate = "0deg";
			document.getElementById("events").appendChild(this.background);
		} else {
			this.background.remove();
			this.obj.style.zIndex = this.zIndex;
			this.obj.style.left = this.x + "px";
			this.obj.style.top = this.y + "px";
			this.obj.style.rotate = this.rotation + "deg";
			this.locked = false;
		}
	}

};

class Timeline {

	constructor(start, ticks) {
		let day = parseInt(start.split("-")[0]);
		let month = parseInt(start.split("-")[1]);
		let year = parseInt(start.split("-")[2]);
		this.start = new Date(year, month, day);
		this.offset = ticks;
		this.current = day;
		this.time = [];
		let timeline = document.getElementById("timeline");
		for ( let i = 1; i <= ticks; ++i ) {
			let tmp = document.createElement("div");
			tmp.classList.add("timeline_tick");
			tmp.innerText = day + i;
			timeline.appendChild(tmp);
		}

	}

}

document.getElementById("create").addEventListener("click", (e) => {
	new Event("asdasd asd asd asd  asd fdg fd g", " sdf sf sdf sdf thdfgfASFDS SDF SDDF SDFAs dh g", Math.random() * 100, Math.random() * 100);
})

new Timeline("25-06-2020", 10);