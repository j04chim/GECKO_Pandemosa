class Line {
	constructor(x, y) {
		this.start_x = x;
		this.start_y = y;
	}
}

class Note {

	constructor(text, x, y) {

		this.x = document.body.clientWidth;
		this.y = (Math.random() * 10000) % window.screen.height;
		this.rotation = 0;
		this.old_mouse_x = -1;
		this.old_mouse_y = -1;
		this.mouseclick = false;
		this.locked = false;

		this.obj = document.createElement("div");
		let header = document.createElement("div");
		let content = document.createElement("div");
		let textarea = document.createElement("textarea");
		this.button_zoom = document.createElement("button");

		textarea.innerText = text;

		this.button_zoom.innerText = "Zoom";

		textarea.classList.add("note_text");
		content.classList.add("note_content");
		header.classList.add("note_header");
		this.button_zoom.classList.add("note_zoom");
		this.obj.classList.add("note");
		this.obj.classList.add("note-" + Math.ceil(Math.random()*10%4));

		this.zoom = this.zoom.bind(this);
		this.button_zoom.addEventListener("click", this.zoom);

		header.appendChild(this.button_zoom);
		content.appendChild(textarea);

		this.obj.appendChild(header);
		this.obj.appendChild(content);

		this.mousemoveto = this.mousemoveto.bind(this);
		this.click = this.click.bind(this);
		this.release = this.release.bind(this);
		this.moveto = this.moveto.bind(this);

		this.obj.style.left =  document.body.clientWidth + "px";
		this.obj.style.top = window.screen.height + "px";

		this.obj.addEventListener("mousemove", this.mousemoveto);
		this.obj.addEventListener("mousedown", this.click);
		this.obj.addEventListener("mouseup", this.release);
		this.obj.addEventListener("mouseleave", this.release);

		document.getElementById("events").appendChild(this.obj);

		this.zIndex = this.obj.style.zIndex;

		this.moveto(x, y, 60)

	}

	cubicBezier(x1, y1, x2, y2) {
		const cx = 3 * x1, bx = 3 * (x2 - x1) - cx, ax = 1 - cx - bx;
		const cy = 3 * y1, by = 3 * (y2 - y1) - cy, ay = 1 - cy - by;
		function sampleCurveX(t) { return ((ax * t + bx) * t + cx) * t; }
		function sampleCurveY(t) { return ((ay * t + by) * t + cy) * t; }
		function sampleCurveDerivativeX(t) { return (3 * ax * t + 2 * bx) * t + cx; }
		function solveCurveX(x, epsilon = 1e-6) {
			let t = x;
			for (let i = 0; i < 8; i++) {
				const xEst = sampleCurveX(t) - x;
				const d = sampleCurveDerivativeX(t);
				if (Math.abs(xEst) < epsilon) return t;
				if (Math.abs(d) < 1e-6) break;
				t -= xEst / d;
			}
			let t0 = 0, t1 = 1, tMid = x;
			while (t0 < t1) {
				tMid = (t0 + t1) / 2;
				const xEst = sampleCurveX(tMid);
				if (Math.abs(xEst - x) < epsilon) return tMid;
				if (xEst > x) t1 = tMid; else t0 = tMid;
			}
			return tMid;
		}
		return function (x) {
			if (x <= 0) return 0;
			if (x >= 1) return 1;
			return sampleCurveY(solveCurveX(x));
		};
	}

	moveto(x, y, steps = 20, bezier = [.09,.71,.17,.99]) {
		const ease = this.cubicBezier(...bezier);
		const startX = this.x, startY = this.y;
		const duration = Math.max(1, steps);
		let frame = 0;

		const animate = () => {
			frame++;
			const linearT = frame / duration;
			const t = ease(linearT);
			this.x = startX + (x - startX) * t;
			this.y = startY + (y - startY) * t;
			this.obj.style.left = this.x + "px";
			this.obj.style.top = this.y + "px";
			if (frame < duration) requestAnimationFrame(animate);
		};
		requestAnimationFrame(animate);
	}

	mousemoveto(e) {

		if ( !this.locked && this.mouseclick ) {

			let mvx = e.pageX - this.old_mouse_x;
			let mvy = e.pageY - this.old_mouse_y;
			this.x += mvx;
			this.y += mvy;
			this.obj.style.left = this.x + "px";
			this.obj.style.top = this.y + "px";
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
			document.getElementById("events").appendChild(this.background);
		} else {
			this.background.remove();
			this.obj.style.zIndex = this.zIndex;
			this.obj.style.left = this.x + "px";
			this.obj.style.top = this.y + "px";
			this.locked = false;
		}
	}

	edit() {

	}

	save() {

	}

	destroy() {
		this.obj.remove();
	}

};