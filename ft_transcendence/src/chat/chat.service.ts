import { Injectable } from '@nestjs/common';

@Injectable()
export class ChatService {
	tab: any[] = ["test", "test2"];

	getData(): any[] {
		return this.tab;
	}
}
