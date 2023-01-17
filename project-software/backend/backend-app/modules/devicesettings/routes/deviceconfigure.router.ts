import express from 'express';

const deviceconfigureRouter = express.Router();

deviceconfigureRouter.get('/deviceconfigure/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`device configure sn: ${sn}`);
});

deviceconfigureRouter.put('/deviceconfigure/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`update one device sn: ${sn}`);
});

deviceconfigureRouter.delete('/deviceconfigure/:serialNumber', (req, res) => {
  const sn: number = +req.params.serialNumber;
  res.send(`update one device sn: ${sn}`);
});

export default deviceconfigureRouter;
