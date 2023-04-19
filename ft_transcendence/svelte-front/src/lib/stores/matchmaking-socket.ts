import type { Socket } from "socket.io-client";
import { writable } from "svelte/store";

export const matchSocket = writable<Socket>(undefined);