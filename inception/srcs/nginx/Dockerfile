FROM alpine:3.16

RUN apk update && apk upgrade && apk add openrc nginx && mkdir /www

WORKDIR /www

EXPOSE 443

CMD rc-service nginx start
