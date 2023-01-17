import express from 'express';

const devicesuperviseRouter = express.Router();

devicesuperviseRouter.get('/devicesupervise/data/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`device configure sn: ${sn}`);
});

devicesuperviseRouter.get(
  '/devicesupervise/alerts/:serialNumber',
  (req, res) => {
    const sn: number = +req.params.serialNumber;
    res.send(`device configure sn: ${sn}`);
  }
);

devicesuperviseRouter.get(
  '/devicesupervise/dashboard/:serialNumber',
  (req, res) => {
    const sn: number = +req.params.serialNumber;
    res.send(`device configure sn: ${sn}`);
  }
);

export default devicesuperviseRouter;
