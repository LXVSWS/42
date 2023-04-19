import type { Profile } from "./profile";

export interface Match {
	opponentScore: number;
	opponentProfile: Profile;
	userScore: number;
	result: string;
	createdAt: Date;
}
