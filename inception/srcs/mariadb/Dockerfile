FROM alpine:3.16

RUN apk add --no-cache mariadb mariadb-client
RUN mariadb-install-db --user=mysql --datadir=/var/lib/mysql

COPY my.cnf /etc/

EXPOSE 3306

CMD ["mysqld_safe"]
