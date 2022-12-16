FROM alpine:3.16

RUN apk update && apk upgrade && apk add openrc nginx && mkdir /www

WORKDIR /www

CMD nginx -g 'daemon off;'
