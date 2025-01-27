import 'dotenv/config';

const ENV = {
  MONGO_URL: process.env.MONGO_URL as string,
  JWT_SECRET: process.env.JWT_SECRET as string,
  AUTH0_SECRET: process.env.AUTH0_SECRET as string,
  AUTH0_BASE_URL: process.env.AUTH0_BASE_URL as string,
  AUTH0_CLIENT_ID: process.env.AUTH0_CLIENT_ID as string,
  AUTH0_ISSUER: process.env.AUTH0_ISSUER as string,
  API_JWKS_URI: process.env.API_JWKS_URI as string,
  API_AUDIENCE: process.env.API_AUDIENCE as string,
};

export default ENV;
