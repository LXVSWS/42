up:
	docker-compose -f srcs/docker-compose.yml up -d

stop:
	docker-compose -f srcs/docker-compose.yml stop

start:
	docker-compose -f srcs/docker-compose.yml start

down:
	docker-compose -f srcs/docker-compose.yml down

ls:
	echo "\n" && docker ps -a && echo "\nIMAGE ID\t\tSIZE\t\tIMAGE" && \
	docker images -a --format "{{.ID}}\t\t{{.Size}}\t\t{{.Repository}}"

clean:
	docker system prune -f

rm:
	docker system prune -af --volumes

mariadb:
	docker exec -it mariadb /bin/sh

nginx:
	docker exec -it nginx /bin/sh

wordpress:
	docker exec -it wordpress /bin/sh


.PHONY:	up stop start down ls clean rm mariadb nginx wordpress
