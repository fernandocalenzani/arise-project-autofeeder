import { connect, Mongoose, set } from 'mongoose';

export default class DBConnection {
  private instance: Mongoose | undefined;
  private url_connection: string;

  constructor(url_connection: string) {
    this.url_connection = url_connection;
  }

  async createConnection() {
    try {
      this.instance = set('strictQuery', false);
      this.instance = await connect(this.url_connection);
      console.log('Database connected successfully');
    } catch (error) {
      console.error(error);
    }
  }
}
