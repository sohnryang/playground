import argparse
import sys

import torch
from torch import nn
from torch.utils.data import DataLoader

sys.path.append(".")

from dataset import test_dataloader, train_dataloader
from model import NeuralNetwork


def train(
    dataloader: DataLoader,
    model: nn.Module,
    loss_fn: nn.Module,
    optimizer: torch.optim.Optimizer,
):
    size = len(dataloader.dataset)  # type: ignore
    model.train()
    for batch, (X, y) in enumerate(dataloader):
        X, y = X.to(device), y.to(device)
        pred = model(X)
        loss = loss_fn(pred, y)

        optimizer.zero_grad()
        loss.backward()
        optimizer.step()

        if batch % 100 == 0:
            loss, current = loss.item(), batch * len(X)
            print(f"loss={loss:>7f} [{current:>5d}/{size:>5d}]")


def test(dataloader: DataLoader, model: nn.Module, loss_fn: nn.Module):
    size = len(dataloader.dataset)  # type: ignore
    num_batches = len(dataloader)
    model.eval()
    test_loss, correct = 0, 0
    with torch.no_grad():
        for X, y in dataloader:
            X, y = X.to(device), y.to(device)
            pred = model(X)
            test_loss += loss_fn(pred, y).item()
            correct += (pred.argmax(1) == y).type(torch.float).sum().item()
    test_loss /= num_batches
    correct /= size
    print("Test error:")
    print(f"acc={(100*correct):>0.1f}%, loss={test_loss:>8f}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser()
    parser.add_argument("-d", "--device", default="cpu", type=str)
    parser.add_argument("-o", "--output", default="model_state.dat", type=str)
    args = parser.parse_args()

    device = args.device
    print(f"Using device: {device}")
    model = NeuralNetwork().to(device)
    loss_fn = nn.CrossEntropyLoss()
    optimizer = torch.optim.SGD(model.parameters(), lr=1e-3)

    epochs = 5
    for t in range(epochs):
        print(f"Epoch {t}")
        train(train_dataloader, model, loss_fn, optimizer)
        test(test_dataloader, model, loss_fn)

    torch.save(model.state_dict(), args.output)
