up:
	docker-compose -f srcs/docker-compose.yml up -d
	docker tag inception-mariadb mariadb:alpine-3.16
	docker tag inception-nginx nginx:alpine-3.16
	docker tag inception-wordpress wordpress:alpine-3.16
	docker image rm inception-mariadb
	docker image rm inception-nginx
	docker image rm inception-wordpress
	clear && make ls

ls:
	docker ps -a
	docker image ls -a

stop:
	docker-compose -f srcs/docker-compose.yml stop

start:
	docker-compose -f srcs/docker-compose.yml start

down:
	docker system prune -f

rm:
	docker system prune -af --volumes

mariadb:
	docker exec -it mariadb /bin/sh

nginx:
	docker exec -it nginx /bin/sh

wordpress:
	docker exec -it wordpress /bin/sh


.PHONY:	up ls stop start down rm mariadb nginx wordpress
