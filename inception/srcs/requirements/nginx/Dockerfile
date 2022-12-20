FROM alpine:3.16

RUN apk add --no-cache nginx

ADD tools /certs

COPY conf/nginx.conf /etc/nginx

CMD ["nginx", "-g", "daemon off;"]
