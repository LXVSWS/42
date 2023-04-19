all: build

build:
	docker-compose up -d --build

down:
	docker-compose down

clean: down
	docker container prune -f
	docker image prune -f
	docker network prune -f

fclean: down
	docker system prune -a

re: clean build

postgres:
	docker run --name postgres \
	 -d \
	 -p 5432:5432 \
	 -e POSTGRES_PASSWORD=passwd \
	 postgres 

pgadmin:
	docker run --name pgadmin \
	-d \
	-p 5050:80 \
	-e 'PGADMIN_DEFAULT_EMAIL=user@gmail.com' \
    -e 'PGADMIN_DEFAULT_PASSWORD=pass' \
    dpage/pgadmin4

.PHONY: build down clean fclean re postgres pgadmin
