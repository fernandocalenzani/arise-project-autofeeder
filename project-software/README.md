# ARISE TECHNOLOGY APPS

In this repo you can find all the applications developed and owned by <span style="font-weight:400">BMS Technology</span>.

1° - build: yarn nx build nest-autofeeder
2° - db gen: yarn prisma generate --schema=./apps/autofeeder-app/prisma/schema.prisma
3° - db push: yarn prisma db push --schema=./apps/autofeeder-app/prisma/schema.prisma

yarn install && build && dbgen && dbpush

## Git commit

#### Branches

main branches

- main
- develop

implementation branches

- bugfix
- feature
- improvement

Dump branches

- dump

#### Commits type

stardart commits:

- test: changing test codes

- feat: development of a new feature to the project

- refactor: code refactoring that doesn't have any kind of impact on the logic/rules

- style: code formatting and style changes that do not change the system in any way

- fix: correction of errors that are generating bugs in the system

- chore: design changes that do not affect the system or test files.

- docs: documentation

- build: used to indicate changes that affect the project's build process or external dependencies

- perf: indicates a change that improved system performance

- ci: used for changes in CI configuration files

- revert: indicates reverting a previous commit

## Apps

1. Expo Autofeeder - React Native Application built using expo for the Autofeeder project.
2. Nest Autofeeder - This application refers to the backend service for the Autofeeder project. It is built TypeScript with the NestJs framework.

## Setting up a local development environment

In order to run a local development environment you need the following:

1. Set up a local Mongo DB instance
2. Run the Nest Autofeeder Application Locally
3. Expose your localhost to the web (needed so expo apps can communicate with local api)
4. Run the Expo Autofeeder Application Locally

### 1. Local Mongo DB Instance

For development, it's recommended to run local instance of mongo db. For that, you can find the following scripts in the <span style="font-weight:bold">package.json</span> file:

```
"db:dev:rm": "sudo docker compose rm dev-db -s -f -v",
"db:dev:up": "sudo docker compose up dev-db -d",
"db:dev:restart": "npm run db:dev:rm && npm run db:dev:up"
```

### 2. Running Nest Autofeeder Application Locally

Just run the script bellow or run it using Nx Console extension (VSCode).

```
npx nx serve nest-autofeeder
```

### 3. Expose Your LocalHost to the Web

In order to <a href="https://dsinecos.github.io/blog/How-to-call-a-locally-hosted-server-from-expo-app" target="_blank">call a locally hosted server from Expo</a> you need to expose the server port to the web (or run the server on 0.0.0.0). To expose you local server to the web, run the following script:

```
npm run localtunnel
```

### 4. Running Expo Autofeeder Application Locally

```
npx nx run expo-autofeeder:start
```
