class Network {

	constructor(url) {
		this.url = url;
	}

	buildUrl(path, params = {}) {
		const url = new URL(path, this.url);
		Object.entries(params).forEach(([k, v]) => {
			if (v !== undefined && v !== null) url.searchParams.set(k, String(v));
		});
		return url.toString();
	}

	async getJson(url) {
		const res = await fetch(url, { method: 'GET' });
		if (!res.ok) throw new Error(`HTTP ${res.status}: ${res.statusText}`);
		return res.json();
	}

	getEvents({ id, dt, dl, dr, ul } = {}) {
		const url = this.buildUrl('/getEvents', {
			id,
			dt,
			dl,
			dr,
			ul
		});
		return this.getJson(url);
	}

	createSession(params = {}) {
		const url = this.buildUrl('/createSession');
		return this.getJson(url);
	}

	getSession(id) {
		if (id === undefined || id === null)
			return Promise.reject(new Error('id is required'));
		const url = this.buildUrl('/getSession', { id });
		return this.getJson(url);
	}

	createNote({ sd, tt, ct } = {}) {
		if (!sd)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/createNote', {
			sd,
			tt,
			ct
		});
		return this.getJson(url);
	}

	getNotes(sd) {
		if (sd === undefined || sd === null)
			return Promise.reject(new Error('sessionId is required'));
		const url = this.buildUrl('/getNotes', { sd });
		return this.getJson(url);
	}

	createAction({ sd, rd, ac, ds } = {}) {
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
		return this.getJson(url);
	}
}