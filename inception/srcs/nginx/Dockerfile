FROM alpine:3.16

RUN apk add --no-cache nginx

COPY nginx.conf /etc/nginx

CMD ["nginx", "-g", "daemon off;"]
