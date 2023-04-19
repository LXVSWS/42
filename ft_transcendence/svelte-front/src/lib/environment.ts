export const environment = {
	apiHost: import.meta.env.VITE_HOST,
	apiPort: import.meta.env.VITE_NESTJS_PORT,
	clientId: import.meta.env.VITE_INTRA_CLIENT_UID,
}

export const apiUrl = `http://${environment.apiHost}:${environment.apiPort}`;
export const intraLoginUrl = `https://api.intra.42.fr/oauth/authorize?client_id=${environment.clientId}&redirect_uri=http%3A%2F%2F${environment.apiHost}%3A${environment.apiPort}%2Fauth%2Flogin&response_type=code`