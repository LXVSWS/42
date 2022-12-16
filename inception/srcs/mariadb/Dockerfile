FROM alpine:3.16

RUN apk update && apk upgrade && apk add openrc mariadb

VOLUME /db_data

CMD rc-service mariadb start
