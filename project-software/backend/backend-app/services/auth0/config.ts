import ENV from '../../infra/config/env';

export const auth0Config = {
  authRequired: false,
  auth0Logout: true,
  secret: ENV.AUTH0_SECRET,
  baseURL: ENV.AUTH0_BASE_URL,
  clientID: ENV.AUTH0_CLIENT_ID,
  issuerBaseURL: ENV.AUTH0_ISSUER,
};
