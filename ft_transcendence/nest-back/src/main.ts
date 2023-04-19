import { NestFactory } from '@nestjs/core';
import { AppModule } from './app.module';
import * as cookieParser from "cookie-parser";
import { ValidationPipe } from '@nestjs/common';
import { json } from 'express';
import { ConfigService } from '@nestjs/config';

async function bootstrap() {
	const app = await NestFactory.create(AppModule);

	const configService = app.get(ConfigService);

	app.enableCors({
		origin: [
			// `http://${configService.get("VITE_HOST")}:${configService.get("SVELTEKIT_PORT")}`
			`http://${configService.get("VITE_HOST")}`
		],
		credentials: true,
		methods: [
			"GET",
			"POST",
			"PATCH",
			"OPTION"
		]
	});
	app.use(cookieParser());
	app.use(json({ limit: "50mb" }));
	app.useGlobalPipes(new ValidationPipe());
	await app.listen(configService.get("VITE_NESTJS_PORT"));
}
bootstrap();
