FROM alpine:3.16

RUN apk add --no-cache php8 \
	php8-fpm \
	php8-curl \
	php8-dom \
	php8-exif \
	php8-fileinfo \
	php8-json \
	php8-mbstring \
	php8-mysqli \
	php8-openssl \
	php8-sodium \
	php8-xml \
	php8-zip

ADD tools/wp.tar.gz /

COPY conf/php-fpm.conf /etc/php8

EXPOSE 9000

CMD ["php-fpm8", "-F", "-p", "/"]
