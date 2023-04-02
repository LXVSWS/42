import { Module } from '@nestjs/common';
import { AppController } from './app.controller';
import { AppService } from './app.service';
import { ServeStaticModule } from '@nestjs/serve-static';
import { join } from 'path';
import { ChatModule } from './chat/chat.module';
import { ChatGateway } from './chat.gateway';

@Module({
  imports: [
	ServeStaticModule.forRoot({
		rootPath: join(__dirname, '..', 'src'),
		serveRoot: '/',
	}),
	ChatModule],
  controllers: [AppController],
  providers: [AppService, ChatGateway],
})
export class AppModule {}
