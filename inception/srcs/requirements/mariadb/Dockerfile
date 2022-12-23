FROM alpine:3.16

RUN apk add --no-cache mariadb mariadb-client

RUN mariadb-install-db --datadir=/var/lib/mysql

COPY conf/my.cnf /etc/

COPY conf/init.sh /

RUN chmod +x /init.sh

EXPOSE 3306

CMD ["mysqld_safe"]
