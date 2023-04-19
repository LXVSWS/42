import { writable } from "svelte/store";
import type { UserType } from "../types/user";

export const user = writable<UserType>(undefined);
