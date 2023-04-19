import { writable } from "svelte/store";
import type { Notification } from "$lib/types/notification";

export const notifications = writable<Notification[]>([]);