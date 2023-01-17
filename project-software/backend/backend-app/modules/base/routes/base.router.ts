import express from 'express';

const baseRouter = express.Router();

baseRouter.get('/', (req, res) => {
  res.send(`HOME`);
});

baseRouter.get('/me', (req, res) => {
  res.send(`my user`);
});

export default baseRouter;
