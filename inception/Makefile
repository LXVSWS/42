up:
	docker-compose -f srcs/docker-compose.yml up
	docker tag inception-db db:alpine-3.16
	docker tag inception-nginx nginx:alpine-3.16
	docker tag inception-php php:alpine-3.16
	docker image rm inception-db
	docker image rm inception-nginx
	docker image rm inception-php
	clear && make ls

down:
	docker system prune -f

ls:
	docker ps -a
	docker image ls -a

rm:
	docker system prune -af --volumes

db:
	docker run -it --rm db:alpine-3.16 /bin/sh

nginx:
	docker run -it --rm nginx:alpine-3.16 /bin/sh

php:
	docker run -it --rm php:alpine-3.16 /bin/sh


.PHONY:	up down ls rm db nginx php
