import type { Friend } from "$lib/types/friend";
import { writable } from "svelte/store";

export const friends = writable<Friend[]>([]);