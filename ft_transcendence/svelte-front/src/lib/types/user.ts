import type { Profile } from "./profile";

export type UserType = {
	id: number
	isTwoFactorAuthenticationEnabled: boolean,
	profile: Profile,
}
