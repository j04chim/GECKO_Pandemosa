class Menu {

	constructor(pandemosa, x, y) {

		this.x = -500;
		this.y = -500;
		this.rotation = 0;
		this.old_mouse_x = -1;
		this.old_mouse_y = -1;
		this.mouseclick = false;
		this.locked = false;
		this.weight = (Math.random() * 10) % 15;
		this.weight = 6;
        this.pandemosa = pandemosa;

        this.obj = document.createElement("div");
        let button_start = document.createElement("button");
        let button_continue = document.createElement("button");

        button_start.innerText = "New game";
        button_continue.innerText = "Continue";

        this.obj.id = "welcome_menu";
        button_start.id = "welcome_start";
        button_continue.id = "welcome_continue";

        let session = localStorage.getItem("session");
        if (session) {
            button_continue.addEventListener("click", (e) => {
                this.pandemosa.displayGame();
                this.pandemosa.loadGame(session);
            })
        } else {
            button_continue.classList.add("unselect")
        }

        button_start.addEventListener("click", (e) => {
            this.pandemosa.displayGame();
            this.pandemosa.createNewGame();
        })

		this.obj.style.left =  "-500px";
		this.obj.style.top = "-500px";
		this.obj.style.rotate = "0deg";

        this.obj.appendChild(button_start);
        this.obj.appendChild(button_continue);

        document.getElementById("pandemosa").appendChild(this.obj);

		this.mousemoveto = this.mousemoveto.bind(this);
		this.click = this.click.bind(this);
		this.release = this.release.bind(this);
		this.moveto = this.moveto.bind(this);

		this.obj.addEventListener("mousemove", this.mousemoveto);
		this.obj.addEventListener("mousedown", this.click);
		this.obj.addEventListener("mouseup", this.release);
		this.obj.addEventListener("mouseleave", this.release);


		this.zIndex = this.obj.style.zIndex;

		this.moveto(x, y, (Math.random() * 100) % (this.weight * 2) - this.weight, 60)

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

	moveto(x, y, r, steps = 20, bezier = [.09,.71,.17,.99]) {
        console.log(x, y);
		const ease = this.cubicBezier(...bezier);
		const startX = this.x, startY = this.y, startR = this.rotation;
		const duration = Math.max(1, steps);
		let frame = 0;

		const animate = () => {
			frame++;
			const linearT = frame / duration;
			const t = ease(linearT);
			this.x = startX + (x - startX) * t;
			this.y = startY + (y - startY) * t;
			this.rotation = startR + (r - startR) * t;
			this.obj.style.left = this.x + "px";
			this.obj.style.top = this.y + "px";
			this.obj.style.rotate = this.rotation + "deg";
			if (frame < duration) requestAnimationFrame(animate);
		};
		requestAnimationFrame(animate);
	}

	mousemoveto(e) {

        e.preventDefault();

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

        e.preventDefault();

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

	destroy() {
		this.obj.remove();
	}

};