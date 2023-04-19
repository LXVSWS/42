import { eventsSocket } from "$lib/stores/events-socket";
import { matchSocket } from "$lib/stores/matchmaking-socket";
import { get } from "svelte/store";

export function sendGameRequest(username: string) {
	const socket = get(eventsSocket);
	const matchSocketTmp = get(matchSocket);
	socket.emit("send-game-request", username);
	matchSocketTmp.emit("newGameRequest", username);
}