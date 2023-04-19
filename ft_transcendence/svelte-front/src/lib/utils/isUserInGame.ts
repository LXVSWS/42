import { eventsSocket } from "$lib/stores/events-socket";
import { get } from "svelte/store";

export async function isUserInGame(username: string): Promise<boolean> {
	const socket = get(eventsSocket);
	return new Promise((resolve, reject) => {
		socket.emit("is-user-in-game", username, (isInGame: boolean) => {
			resolve(isInGame);
		});
	});
}