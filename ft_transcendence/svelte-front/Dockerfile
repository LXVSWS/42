FROM node:19-alpine

WORKDIR /usr/src/app

COPY package*.json ./

RUN npm ci

COPY . .

ARG VITE_HOST
ARG VITE_NESTJS_PORT
ARG SVELTEKIT_PORT
ARG VITE_INTRA_CLIENT_UID

RUN npm run build

ENV PORT=${SVELTEKIT_PORT}
ENV HOST=0.0.0.0

CMD [ "node", "build" ]
