FROM alpine:3.16

RUN apk add --no-cache php8-fpm

ADD wp.tar.gz /

COPY php-fpm.conf /etc/php8

EXPOSE 9000

CMD ["php-fpm8"]
