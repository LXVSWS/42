FROM alpine:3.16

RUN apk add --no-cache lighttpd

ADD tools /var/www/localhost/htdocs

CMD ["lighttpd", "-D", "-f","/etc/lighttpd/lighttpd.conf"]
