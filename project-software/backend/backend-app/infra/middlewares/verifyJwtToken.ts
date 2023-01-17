import { GetVerificationKey, expressjwt } from 'express-jwt';
import * as jwksRsa from 'jwks-rsa';
import ENV from '../config/env';

export const verifyJwtToken = expressjwt({
  secret: jwksRsa.expressJwtSecret({
    cache: true,
    rateLimit: true,
    jwksRequestsPerMinute: 5,
    jwksUri: ENV.API_JWKS_URI,
  }) as GetVerificationKey,
  audience: ENV.API_AUDIENCE,
  issuer: ENV.AUTH0_ISSUER,
  algorithms: ['RS256'],
});
