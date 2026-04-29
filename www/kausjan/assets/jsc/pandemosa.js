class Event {

	constructor(title, desc) {

		this.obj = document.createElement("div");
		let header = document.createElement("div");
		let content = document.createElement("div");
		let rtitle = document.createElement("h2");
		let description = document.createElement("p");
		let footer = document.createElement("div");
		let button_pass = document.createElement("button");
		let button_act = document.createElement("button");
		let button_zoom = document.createElement("button");

		rtitle.innerText = title;
		description.innerText = desc;
		button_act.innerText = "Act";
		button_pass.innerText = "Pass";
		button_zoom.innerText = "Zoom";

		button_act.classList.add("event_button");
		button_act.classList.add("event_act");
		button_pass.classList.add("event_button");
		button_pass.classList.add("event_pass");
		footer.classList.add("event_footer");
		rtitle.classList.add("event_title");
		description.classList.add("event_desc");
		content.classList.add("event_content");
		header.classList.add("event_header");
		button_zoom.classList.add("event_zoom");
		this.obj.classList.add("event");

		header.appendChild(button_zoom);
		footer.appendChild(button_act);
		footer.appendChild(button_pass);
		content.appendChild(rtitle);
		content.appendChild(description);

		this.obj.appendChild(header);
		this.obj.appendChild(content);
		this.obj.appendChild(footer);

		document.getElementById("events").appendChild(this.obj);

	}

};

let e = new Event("a", "b");