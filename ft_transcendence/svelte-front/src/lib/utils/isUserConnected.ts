import { eventsSocket } from "$lib/stores/events-socket";
import { get } from "svelte/store";

export async function isUserConnected(username: string): Promise<boolean> {
	const socket = get(eventsSocket);
	return new Promise((resolve, reject) => {
		socket.emit("is-user-connected", username, (isLoggedIn: boolean) => {
			resolve(isLoggedIn);
		});
	});
}