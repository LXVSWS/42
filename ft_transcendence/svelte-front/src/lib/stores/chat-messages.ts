import type { chatMessage } from "$lib/types/chat-messages";
import { writable } from "svelte/store";

export const chatMessages = writable<chatMessage>({});