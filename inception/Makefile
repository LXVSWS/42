up:
	mkdir -p /home/lwyss/data/db /home/lwyss/data/wp
	docker compose -f srcs/docker-compose.yml up -d --build --force-recreate
	docker exec mariadb ./init.sh
	curl -k https://lwyss.42.fr/wp-admin/install.php\?step\=2 | grep "<code>"

stop:
	docker compose -f srcs/docker-compose.yml stop

start:
	docker compose -f srcs/docker-compose.yml start

down:
	docker compose -f srcs/docker-compose.yml down

ls:
	echo "\n" && docker ps -a && echo "\nIMAGE ID\t\tSIZE\t\tIMAGE" && \
	docker images -a --format "{{.ID}}\t\t{{.Size}}\t\t{{.Repository}}"

log:
	docker exec -it nginx cat /var/log/nginx/access.log
	docker exec -it nginx cat /var/log/nginx/error.log
	docker logs nginx

logs:
	docker exec -it wordpress cat var/log/php8/access.log
	docker exec -it wordpress cat var/log/php8/error.log
	docker logs wordpress

clean:
	docker system prune -f

vol:
	docker volume rm db wp
	rm -rf /home/lwyss/data

rm:
	docker system prune -af

mariadb:
	docker exec -it mariadb /bin/sh

nginx:
	docker exec -it nginx /bin/sh

wordpress:
	docker exec -it wordpress /bin/sh


.PHONY:	up stop start down ls log logs clean vol rm mariadb nginx wordpress
