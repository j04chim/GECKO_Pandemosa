class Network {

	constructor(url, sid) {
		this.url = url;
        this.sid = sid;
	}

	buildUrl(path, params = {}) {
		const url = new URL(path, this.url);
		Object.entries(params).forEach(([k, v]) => {
			if (v !== undefined && v !== null) url.searchParams.set(k, v);
		});
		return url.toString();
	}

	async getJson(url) {
		const res = await fetch(url, { method: 'GET' });
		if (!res.ok) throw new Error(`HTTP ${res.status}: ${res.statusText}`);
		return res.json();
	}

	async getEvents({ id, dt, dl, dr, ul } = {}) {
		const url = this.buildUrl('/getEvents', {
			id,
			dt,
			dl,
			dr,
			ul
		});
		return await this.getJson(url);
	}

	async createSession(params = {}) {
		const url = this.buildUrl('/createSession');
        let json = await this.getJson(url);
        this.sid = json.id;
        console.log(json)
		return json;
	}

	async getSession(id) {
		if (id === undefined || id === null)
			return Promise.reject(new Error('id is required'));
		const url = this.buildUrl('/getSession', { id });
        this.sid = id;
		return await this.getJson(url);
	}

	async createNote({ sd = this.sid, tt, ct } = {}) {
		if (!sd)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/createNote', {
			sd,
			tt,
			ct
		});
		return await this.getJson(url);
	}

	async createNoteLink({ sd = this.sid, na, nb } = {}) {
		if (!sd)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/createNoteLink', {
			sd,
			na,
			nb
		});
		return await this.getJson(url);
	}

	async getNoteLink({ sd = this.sid } = {}) {
		if (!sd)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/getNoteLink', {
			sd
		});
		return await this.getJson(url);
	}

	async deleteNote({ nid } = {}) {
		if (!nid)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/deleteNote', {
			nid,
		});
		return await this.getJson(url);
	}

	async updateNote({ nid, tt, ct } = {}) {
		if (!nid)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/updateNote', {
			nid,
			tt,
			ct
		});
		return await this.getJson(url);
	}

	async getNotes({sd = this.sid} = {}) {
		if (sd === undefined || sd === null)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/getNotes', { sd });
		return await this.getJson(url);
	}

	async createAction({ sd, rd, ac, ds } = {}) {
		if (!sd)
			return Promise.reject(new Error('sessionId is required'));
		if (!ac)
			return Promise.reject(new Error('action is required'));
		const url = this.buildUrl('/createAction', {
			sd,
			rd,
			ac,
			ds
		});
		return await this.getJson(url);
	}
}