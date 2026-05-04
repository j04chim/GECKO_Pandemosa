let Events = []
let t = new Timeline("01-06-2020", 10);

document.getElementById("create").addEventListener("click", (e) => {
	new Event("asdasd asd asd asd  asd fdg fd g", " sdf sf sdf sdf thdfgfASFDS SDF SDDF SDFAs dh g", Math.random() * 100, Math.random() * 100);
});

document.getElementById("next").addEventListener("click", (e) => {
	t.next();
});
