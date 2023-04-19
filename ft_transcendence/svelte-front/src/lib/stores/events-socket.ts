import { writable } from "svelte/store";
import type { Socket } from "socket.io-client";

export const eventsSocket = writable<Socket>(undefined);