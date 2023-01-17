import * as express from 'express';
import * as cors from 'cors';
import baseRoutes from './baseRoutes';
import { mongoDBConnection } from '../database';

import { ScheduledTask } from 'node-cron';
import 'dotenv/config';

interface SetupOptions {
  isTest?: boolean;
  port?: number;
}

export default class App {
  private instance: express.Application;
  private defaultPort = 4000;

  constructor() {
    this.instance = express();
  }

  async setupApp(options?: SetupOptions) {
    this.instance.use(cors());
    this.instance.use(express.json());
    this.instance.use(baseRoutes);

    scheduleNotifications.start();
    scheduleUpdateFieldActivityStatus.start();
    await mongoDBConnection.createConnection();
    const selectedPort = options?.port ? options.port : this.defaultPort;

    if (options?.isTest) return;

    this.instance.listen(selectedPort, () =>
      console.log(`Server running in port ${selectedPort}`)
    );
  }

  /** Instantiate an app module to the given routes */
  async setupFunction(routes: express.Router) {
    this.instance.use(cors());
    this.instance.use(express.json());
    this.instance.use(routes);

    await mongoDBConnection.createConnection();

    return this.instance;
  }
}
